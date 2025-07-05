/*********************************************************************
 * @file   Jive.h
 * @brief  .
 * 
 * Project: Excalibur
 * 
 * @author Xander Boosinger (xboosinger@gmail.com)
 * @date   April 2025
 * 
 *********************************************************************
/*
 *			*	/\
 *			   / /	*
 *		*	__/ /__
 *		      /	  *
 *			 /
 */

#pragma once

#include "Enums/Direction.h"

#include <vector>
#include <cassert>

using std::vector;

class JiveIndex
{
public:

	JiveIndex(unsigned int const& RecipeIndex, unsigned int const& MixIndex);

	unsigned int GetRecipeIndex() const { return recipeIndex; }

	unsigned int GetMixIndex() const { return mixIndex; }

private:

	unsigned int recipeIndex;

	unsigned int mixIndex;

};

//template <typename T>
//class AccessInfo
//{
//public:
//
//	JiveIndex const& GetJiveIndex() { return jiveIndex; }
//
//	T* const& GetPointer() { return pointer; }
//
//private:
//
//	JiveIndex jiveIndex;
//
//	T* pointer;
//
//};

template<typename T>
class Ingredient
{
public:

	Ingredient() = default;

	Ingredient(T const& Base) : base(Base){}

	T& GetBase() { return base; }

	void SetBase(T const& Base) { base = Base; }

private:

	T base;

};

class Step
{
public:

	Step(unsigned int Start, unsigned int End) : start(Start), end(End) {}

	void Extend()
	{
		++end;
	}

	/*void Contract(Direction Direction)
	{
		if (Direction)
		{
			--start;
		}
		else
		{
			++end;
		}
	}*/

	unsigned int GetStart() const { return start; }

	unsigned int GetEnd() const { return end; }

	void SetStart(unsigned int Start) { start = Start; }

	void SetEnd(unsigned int End) { end = End; }

private:

	unsigned int start;

	unsigned int end;
};

template<typename T, unsigned int Size>
class Jive
{
public:

	Jive() : recipe({ /*{ Step(0, 0) }*/ }), mix({ /*new Ingredient<T>[Size]*/ })
	{
	}

	Jive(vector<T> const& InitialIngredients)
		: recipe({ /*{ Step(0, 0) }*/ }), mix({ /*new Ingredient<T>[Size]*/ })
	{
		for (int i = 0; i < InitialIngredients.size(); ++i)
		{
			Add(InitialIngredients[i]);
		}
	}

	~Jive()
	{
		for (int i = 0; i < mix.size(); ++i)
		{
			delete [] mix[i];
		}
	}

	T const& operator[](JiveIndex const& index) const
	{
		return mix[index.GetRecipeIndex()][index.GetMixIndex()].GetBase();
	}

	T& operator[](JiveIndex const& index)
	{
		return mix[index.GetRecipeIndex()][index.GetMixIndex()].GetBase();
	}

	T const& operator[](unsigned int recipeIndex, unsigned int mixIndex) const
	{
		return mix[recipeIndex][mixIndex].GetBase();
	}

	T& operator[](unsigned int recipeIndex, unsigned int mixIndex)
	{
		return mix[recipeIndex][mixIndex].GetBase();
	}



	/*unsigned int LargeIndexToMixIndex(unsigned int badIndex)
	{
		return badIndex % Size;
	}

	unsigned int LargeIndexToRecipeIndex(unsigned int badIndex)
	{
		return (unsigned int)(badIndex / Size);
	}

	unsigned int SmallIndexToLargeIndex(unsigned int recipeIndex, unsigned int mixIndex)
	{
		return recipeIndex * Size + mixIndex;
	}*/

	unsigned int FindIngredient(T const* Base)
	{
		for (unsigned int i = 0; i < recipe.size(); ++i)
		{
			for (unsigned int j = 0; j < recipe[i].size(); ++j)
			{
				for (unsigned int k = recipe[i][j].GetStart(); k < recipe[i][j].GetEnd(); ++k)
				{
					if (&mix[i][k].GetBase() == Base)
					{
						return SmallIndexToLargeIndex(i, k);
					}
				}
			}
		}

		return -1;
	}

	JiveIndex Add(T const& Base)
	{
		Base;

		unsigned int emptyRecipeIndex = (unsigned int)recipe.size();
		unsigned int emptyMixIndex = 0;
		for (unsigned int i = 0; i < recipe.size(); ++i)
		{
			 emptyMixIndex = recipe[i][0].GetEnd();

			 if (emptyMixIndex < Size)
			 {
				 emptyRecipeIndex = i;

				 break;
			 }
		}

		if (emptyRecipeIndex == recipe.size())
		{
			recipe.push_back(vector<Step>{Step(0, 0)});

			mix.push_back(new Ingredient<T>[Size]);

			emptyMixIndex = 0;
		}

		
		{
			mix[emptyRecipeIndex][emptyMixIndex] = Ingredient(Base);
			ExtendStep(emptyRecipeIndex, 0);
		}

		CleanRecipe(emptyRecipeIndex);

		return JiveIndex(emptyRecipeIndex, emptyMixIndex);
	}

	void Remove(JiveIndex const& LargeIndex)
	{
		unsigned int recipeIndex = LargeIndex.GetRecipeIndex();
		unsigned int mixIndex = LargeIndex.GetMixIndex();

		unsigned int splittableStep = FindCorrespondingStep(recipeIndex, mixIndex);

		SplitStep(recipeIndex, splittableStep, mixIndex);

		recipe[recipeIndex][splittableStep + 1].SetStart(recipe[recipeIndex][splittableStep + 1].GetStart() + 1);

		CleanRecipe(recipeIndex);
	}
	void Remove(T const* Base)
	{
		Remove(FindIngredient(Base));
	}

	unsigned int FindCorrespondingStep(unsigned int RecipeIndex, unsigned int MixIndex)
	{
		for (int i = 0; i < recipe[RecipeIndex].size(); ++i)
		{
			if (MixIndex >= recipe[RecipeIndex][i].GetStart() && MixIndex < recipe[RecipeIndex][i].GetEnd())
			{
				return i;
			}
		}

		return (unsigned int)recipe.size();
	}

	void ExtendStep(unsigned int RecipeIndex, unsigned int StepIndex)
	{
		recipe[RecipeIndex][StepIndex].Extend();
	}

	void ConcatenateSteps(unsigned int RecipeIndex, unsigned int FirstStep)
	{
		recipe[RecipeIndex][FirstStep] = Step(recipe[RecipeIndex][FirstStep].GetStart(), recipe[RecipeIndex][FirstStep + 1].GetEnd());

		recipe[RecipeIndex].erase(recipe[RecipeIndex].begin() + FirstStep + 1);
	}

	void SplitStep(unsigned int RecipeIndex, unsigned int StepIndex, unsigned int Split)
	{
		recipe[RecipeIndex].insert(recipe[RecipeIndex].begin() + StepIndex + 1, Step(Split, recipe[RecipeIndex][StepIndex].GetEnd()));
		recipe[RecipeIndex][StepIndex].SetEnd(Split);
	}

	void CleanRecipe(unsigned int RecipeIndex)
	{
		if (recipe[RecipeIndex].size() > 1)
		{
			for (unsigned int i = (unsigned int)recipe[RecipeIndex].size() - 2; i >= 1; --i)
			{
				if (recipe[RecipeIndex][i].GetStart() == recipe[RecipeIndex][i].GetEnd())
				{
					recipe[RecipeIndex].erase(recipe[RecipeIndex].begin() + i);
					//--i;
					continue;
				}

				if (recipe[RecipeIndex][i].GetEnd() == recipe[RecipeIndex][i + 1].GetStart())
				{
					ConcatenateSteps(RecipeIndex, i);
					//--i;
				}
			}

			if (recipe[RecipeIndex].size() > 1 && recipe[RecipeIndex][recipe[RecipeIndex].size() - 1].GetStart() == recipe[RecipeIndex][recipe[RecipeIndex].size() - 1].GetEnd())
			{
				recipe[RecipeIndex].erase(recipe[RecipeIndex].begin() + recipe[RecipeIndex].size() - 1);
			}

			if (recipe[RecipeIndex].size() > 1 && recipe[RecipeIndex][0].GetEnd() == recipe[RecipeIndex][1].GetStart())
			{
				ConcatenateSteps(RecipeIndex, 0);
			}
		}
	}

	template<Direction Direction, typename Func>
	constexpr void JiveIterate(Func Function, vector<vector<Step>> const& Recipe)
	{
		switch (Direction)
		{
		case FORWARD:
		{
			for (unsigned int i = 0; i < Recipe.size(); ++i)
			{
				for (unsigned int j = 0; j < Recipe[i].size(); ++j)
				{
					for (unsigned int k = Recipe[i][j].GetStart(); k < Recipe[i][j].GetEnd(); ++k)
					{
						Function(mix[i][k]);
					}
				}
			}

			break;
		}

		//case BACKWARD:
		//{
		//	for (unsigned int i = (unsigned int)recipe.size(); i-- > 0; i)
		//	{
		//		/*if (recipe[i].GetEnd() > 0)
		//		{*/
		//			for (unsigned int j = recipe[i].GetEnd(); j-- > recipe[i].GetStart(); j)
		//			{
		//				Function(mix[j]);
		//			}
		//		//}
		//	}

		//	break;
		//}
		}
	}
	template<Direction Direction, typename Func>
	constexpr void JiveIterate(Func Function)
	{
		JiveIterate<Direction, Func>(Function, this->recipe);
	}

	vector<vector<Step>> const& GetRecipe() const { return recipe; }

private:

	vector<vector<Step>> recipe;

	vector<Ingredient<T>*> mix;

	//char testpadding[1000000];

};
